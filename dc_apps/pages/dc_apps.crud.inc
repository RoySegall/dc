<?php
/**
 * @file
 * Manage here all the pages which relate to CRUD functionallity.
 */

/**
 * Manage an app entity.
 */
function dc_apps_app_form($form, &$form_state, $app = NULL) {
  if (!$app) {
    $app = dc_apps_create();
  }
  $form_state['#entity'] = $app;

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('title'),
    '#description' => t('The name of the application.'),
  );

  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The description of the application'),
  );

  // Get the entities and sort them in alphabetical order.
  $entities = entity_get_info();
  ksort($entities);

  foreach ($entities as $name => $info) {
    $form['need'][$name][$name . '_need'] = array(
      '#type' => 'checkbox',
      '#title' => $info['label'],
    );

    $form['need'][$name][$name . '_search'] = array(
      '#type' => 'select',
      '#title' => t('Search by'),
      '#description' => t('Select the field/property on which apps can make a search.'),
      '#options' => $info['schema_fields_sql']['base table'] + dc_apps_build_fields($name),
      '#states' => array(
        'visible' => array(
          ':input[name="' . $name . '_need"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['need'][$name][$name . '_operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#description' => t('What the operator you would like to apply?'),
      '#options' => array(
        '=' => '=',
        '%LIKE%' => t('Like'),
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="' . $name . '_need"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  $form['additional_settings'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );

  $form['author'] = array(
    '#type' => 'fieldset',
    '#access' => user_access('administer nodes'),
    '#title' => t('Authoring information'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#weight' => 90,
  );

  $form['author']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Authored by'),
    '#maxlength' => 60,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => user_load($app->uid)->name,
    '#weight' => -1,
    '#description' => t('Leave blank for %anonymous.', array('%anonymous' => variable_get('anonymous', t('Anonymous')))),
  );

  $form['oauth'] = array(
    '#type' => 'fieldset',
    '#access' => user_access('administer nodes'),
    '#title' => t('oAuth information'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#weight' => 100,
  );

  $form['oauth']['key'] = array(
    '#type' => 'item',
    '#title' => t('Key'),
    '#markup' => $app->app_key ? $app->app_key : t('Need be generated'),
  );

  $form['oauth']['secret'] = array(
    '#type' => 'item',
    '#title' => t('Secret'),
    '#markup' => $app->app_key ? $app->app_key : t('Need be generated'),
  );

  $form['oauth']['site'] = array(
    '#type' => 'textfield',
    '#title' => t('Site'),
    '#description' => t('Fill in the site address. This will affect the signature and could affect the redirect of the user.'),
  );

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    ),
    'cancel' => array(
      '#type' => 'markup',
      '#markup' => l(t('Cancel'), 'admin/apps'),
    ),
  );

  return $form;
}

/**
 * Validate handler.
 */
function dc_apps_app_form_validate($form, $form_state) {
}

/**
 * Submit handler.
 */
function dc_apps_app_form_submit($form, $form_state) {
}
