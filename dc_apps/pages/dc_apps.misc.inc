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

  $header = array(
    array('data' => t('App name'), 'width' => '40%'),
    array('data' => t('Information'), 'width' => '40%'),
    array('data' => t('Options')),
  );;
  $rows = array();

  foreach ($apps as $app) {
    $params = array(
      '@key' => $app->app_key,
      '@secret' => $app->app_secret,
      '@site' => $app->app_site,
    );

    $links = array();
    $links[] = array(
      'href'  => 'node/',
      'title' => t('Edit'),
    );

    $links[] = array(
      'href'  => 'node/',
      'title' => t('Delete'),
    );

    $links[] = array(
      'href'  => 'node/',
      'title' => t('Documentation'),
    );

    $rows[] = array(
      $app->title . '<br />' . $app->description,
      t('Key: @key<br />Secret: @secret<br />Site: @site', $params),
      theme('links', array(
        'links' => $links,
        'attributes' => array('class' => array('links', 'inline')),
      )),
    );
  }

  $table = array(
    'header' => $header,
    'rows' => $rows,
  );
  $content = theme('table', $table);

  return $content;
}

/**
 * Settings for the Drupal connect apps.
 */
function dc_apps_settings($form, $form_state) {
  return $form;
}
