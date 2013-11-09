<?php

/**
 * @file
 * Holds Drupal connect publisher restWS format handler.
 */

class DrupalConnectPublisherRestFormat extends RestWSFormatJSON {

  /**
   * @var
   * Determine if the handler suppose to filter un accessible properties.
   */
  static $filter = TRUE;

  /**
   * Change the value of the filter control.
   */
  public static function setFilter($value) {
    self::$filter = $value;
  }

  /**
   * Gets the representation of a resource.
   *
   * @see RestWSFormatJSON::viewResource().
   */
  public function viewResource($resourceController, $id) {
    $values = self::getData($resourceController->wrapper($id));
    $function = __FUNCTION__;
    drupal_alter('restws_response', $values, $function, $this->formatName);

    return $this->serialize($values);
  }

  /**
   * Gets a simple PHP array using URI references for some wrapped data.
   *
   * This is the counter-part of self::getPropertyValues().
   *
   * @see RestWSFormatJSON::getData().
   */
  public static function getData($wrapper) {
    $data = array();

    // Drupal connect publisher extra: bypassing the wrapper's access callback.
    $filtered = self::$filter ? restws_property_access_filter($wrapper) : $wrapper;

    foreach ($filtered as $name => $property) {
      try {
        if ($property instanceof EntityDrupalWrapper) {
          // For referenced entities only return the URI.
          if ($id = $property->getIdentifier()) {
            $data[$name] = self::getResourceReference($property->type(), $id);
          }
        }
        elseif ($property instanceof EntityValueWrapper) {
          $data[$name] = $property->value();
        }
        elseif ($property instanceof EntityListWrapper || $property instanceof EntityStructureWrapper) {
          $data[$name] = self::getData($property);
        }
      }
      catch (EntityMetadataWrapperException $e) {
        // A property causes problems - ignore that.
      }
    }
    return $data;
  }
}
