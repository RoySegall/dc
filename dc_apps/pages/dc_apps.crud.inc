<?php
/**
 * @file
 * Manage here all the pages which relate to CRUD functionallity.
 */

/**
 * Manage an app entity.
 */
function dc_apps_app_form($form, $form_state) {
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

  $entities = entity_get_info();
  ksort($entities);

  foreach ($entities as $name => $info) {
    $form['need'][$name][$name . '_need'] = array(
      '#type' => 'checkbox',
      '#title' => $info['label'],
    );

    $form['need'][$name][$name . 'search'] = array(
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
    '#attributes' => array(
      'class' => array('node-form-author'),
    ),
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'node') . '/node.js',
        array(
          'type' => 'setting',
          'data' => array('anonymous' => variable_get('anonymous', t('Anonymous'))),
        ),
      ),
    ),
    '#weight' => 90,
  );
  $form['author']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Authored by'),
    '#maxlength' => 60,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => !empty($node->name) ? $node->name : '',
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
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'node') . '/node.js',
        array(
          'type' => 'setting',
          'data' => array('anonymous' => variable_get('anonymous', t('Anonymous'))),
        ),
      ),
    ),
    '#weight' => 100,
  );

  $form['oauth']['key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
  );

  $form['oauth']['secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret'),
  );
  $form['oauth']['Site'] = array(
    '#type' => 'textfield',
    '#title' => t('Site'),
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
