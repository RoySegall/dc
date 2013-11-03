<?php
/**
 * @file
 * Holds the function for the entity api integration.
 */

/**
 * Implements hook_entity_info().
 */
function dc_publisher_entity_info() {
  return array(
    'approved_apps' => array(
      'label' => t('Approved app'),
      'entity class' => 'DrupalPublisherApprovedApp',
      'controller class' => 'EntityAPIController',
      'base table' => 'approved_apps',
      'entity keys' => array(
        'id' => 'id',
      ),
      'load hook' => '',
    ),
    'authorized_sessions' => array(
      'label' => t('Authorized sessions'),
      'entity class' => 'DrupalPublisherAuthorizedSession',
      'controller class' => 'EntityAPIController',
      'base table' => 'authorized_sessions',
      'entity keys' => array(
        'id' => 'id',
      ),
      'load hook' => '',
    ),
  );
}

/**
 * Create Drupal publisher approved app entity.
 *
 * @param $data
 *  Initialize data of the Drupal publisher approved app.
 *
 * @return DrupalPublisherApprovedApp
 *  Initialized object a Drupal publisher approved app.
 */
function dc_publisher_approved_apps_create($data = array()) {
  global $user;

  $data += array(
    'uid' => $user->uid,
    'timestamp' => REQUEST_TIME,
  );

  return entity_create('approved_apps', $data);
}

/**
 * Load multiple Drupal publisher approved app entity.
 *
 * @param $ids
 *  Array of Drupal publisher apps IDs.
 *
 * @return DrupalPublisherApprovedApp[]
 *  Array of Drupal publisher approved apps objects.
 */
function dc_publisher_approved_apps_load_multiple($ids) {
  return entity_load('approved_apps', $ids);
}

/**
 * Load a single Drupal publisher approved app entity.
 *
 * @param $id
 *  Id of a Drupal publisher approved app entity.
 *
 * @return DrupalPublisherApprovedApp
 *  Drupal publisher approved apps object.
 */
function dc_publisher_approved_apps_load($id) {
  $entity = entity_load('approved_apps', array($id));
  return reset($entity);
}

/**
 * Delete multiple Drupal publisher approved app entities.
 *
 * @param $ids
 *  List of Drupal publisher app IDs to delete.
 */
function dc_publisher_approved_apps_delete_multiple($ids) {
  entity_delete_multiple('approved_apps', $ids);
}

/**
 * Create Drupal publisher authorized sessions entity.
 *
 * @param $data
 *  Initialize data of the Drupal authorized sessions.
 *
 * @return DrupalPublisherAuthorizedSession
 *  Initialized object a Drupal publisher authorized sessions.
 */
function dc_publisher_authorized_session_create($data = array()) {
  global $user;

  $data += array(
    'timestamp' => REQUEST_TIME,
  );

  return entity_create('authorized_sessions', $data);
}

/**
 * Load multiple Drupal publisher authorized sessions entity.
 *
 * @param $ids
 *  Array of Drupal publisher sessions IDs.
 *
 * @return DrupalPublisherAuthorizedSession[]
 *  Array of Drupal publisher authorized sessions objects.
 */
function dc_publisher_authorized_session_load_multiple($ids) {
  return entity_load('authorized_sessions', $ids);
}

/**
 * Load a single Drupal publisher authorized sessions entity.
 *
 * @param $id
 *  Id of a Drupal publisher authorized session entity.
 *
 * @return DrupalPublisherAuthorizedSession
 *  Drupal publisher authorized session object.
 */
function dc_publisher_authorized_sessions_load($id) {
  $entity = entity_load('authorized_sessions', array($id));
  return reset($entity);
}

/**
 * Delete multiple Drupal publisher authorized sessions entities.
 *
 * @param $ids
 *  List of Drupal publisher authorized session IDs to delete.
 */
function dc_publisher_authorized_session_delete_multiple($ids) {
  entity_delete_multiple('authorized_sessions', $ids);
}
