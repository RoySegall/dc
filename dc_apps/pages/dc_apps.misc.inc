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

  $apps = array();
  if (!empty($result['dc_app'])) {
    $apps = dc_apps_load_multiple(array_keys($result['dc_app']));
  }

  $header = array(
    array('data' => t('App name'), 'width' => '40%'),
    array('data' => t('Information'), 'width' => '40%'),
    array('data' => t('Options')),
  );

  $rows = array();

  if ($apps) {
    foreach ($apps as $app) {
      $params = array(
        '@key' => $app->app_key,
        '@secret' => $app->app_secret,
        '@site' => $app->app_site,
      );

      $items = array();
      $items[] = $app->generateLink('edit');
      $items[] = $app->generateLink('delete');

      if (!$app->status) {
        $items[] = $app->generateLink('approve');
      }

      // Let other module add their own links.
      drupal_alter('dc_apps_app_options', $items, $app);

      $rows[] = array(
        $app->title . '<br />' . $app->description,
        t('Key: @key<br />Secret: @secret<br />Site: @site', $params),
        theme('item_list', array(
          'items' => $items,
          'attributes' => array('class' => array('links', 'inline')),
        )),
      );
    }
  }
  else {
    $rows[] = array(array('data' => t('No apps were found.'), 'colspan' => 3));
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
  $form['apps_need_approve'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apps need to be approve?'),
    '#description' => t('When apps are created they approve autocratically. You can turn this off by checking the box.'),
    '#default_value' => variable_get('apps_need_approve', FALSE),
  );

  // TODO: Add an option for apps to overrides this option.
  $form['apps_data_number'] = array(
    '#type' => 'textfield',
    '#title' => t('How much results to supply in each request'),
    '#description' => t('When a client ask data from the app you can decide how much to supply each time. 25 by default'),
    '#default_value' => variable_get('apps_data_number', 25),
  );

  $description = 'Apps can search for information on your site.';
  $description .= 'When searching users you can define that only that approve the app will appear in search.';
  $form['apps_search_for_users_limit'] = array(
    '#type' => 'checkbox',
    '#title' => t('When search for user information, display only user which approved the app?'),
    '#description' => t($description),
    '#default_value' => variable_get('apps_search_for_users_limit', FALSE),
  );

  return system_settings_form($form);
}
