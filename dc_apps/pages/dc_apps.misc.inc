<?php
/**
 * @file
 * Manage here all the pages which not relate to CRUD functionallity.
 */

/**
 * Display the main page of the apps.
 */
function dc_apps_main_app_page() {
  $query = new entityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'dc_app')
    ->execute();

  $apps = dc_apps_load_multiple(array_keys($result['dc_app']));

  return '';
}
