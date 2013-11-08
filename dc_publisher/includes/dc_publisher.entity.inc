<?php
/**
 * @file
 * Holds the basic structure of the entity.
 */

/**
 * Class DrupalPublisherApprovedApp extends Entity
 *
 * Holding the object for Drupal publisher approved app.
 */
class DrupalPublisherApprovedApp extends Entity {

  /**
   * @var
   * The identifier.
   */
  public $id;

  /**
   * @var
   * The primary identifier for a applications.
   */
  public $app_id;

  /**
   * @var
   * The {users}.uid that owns this application.
   */
  public $uid;

  /**
   * @var
   * The Unix timestamp when the entry was created.
   */
  public $timestamp;

  /**
   * @var
   * The status of the app - disabled, enabled.
   */
  public $status;

  /**
   * Get the application object.
   *
   * @return DrupalConnectApps
   *  The application object.
   */
  function app() {
    if (!$this->app_id) {
      return;
    }

    return dc_apps_load($this->app_id);
  }
}

/**
 * Class DrupalPublisherAuthorizedSession extends Entity
 *
 * Holds the object of the Drupal publisher authorized session.
 */
class DrupalPublisherAuthorizedSession extends Entity {
  /**
   * @var
   * The identifier.
   */
  public $id;

  /**
   * @var
   * The primary identifier for a applications.
   */
  public $app_id;

  /**
   * @var
   * The session string.
   */
  public $session;

  /**
   * @var
   * The Unix timestamp when the entry was created.
   */
  public $timestamp;

  /**
   * @var
   * The user id which the session created for.
   */
  public $uid;

  /**
   * Create a session string.
   *
   * @param $secret
   *  The secret key of the application.
   *
   * @return DrupalPublisherAuthorizedSession
   */
  public function sessionCreate($secret) {
    $this->session = md5($secret . '_' . REQUEST_TIME);

    return $this;
  }

  /**
   * Return the data of the user.
   *
   * @param $output
   *  Determine if the method need user drupal_json_output and take over the
   *  page content or just return the data of the user.
   *
   * @return mixed
   *  Array of the user information.
   */
  function getUserInfo($output = FALSE) {
    $resource = restws_resource_controller('user');
    $format = restws_format('json');

    $content = drupal_json_decode($format->viewResource($resource, $this->uid, TRUE));

    if ($output) {
      drupal_json_output($content);
      return;
    }

    return $content;
  }
}
