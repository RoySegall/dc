<?php
/**
 * @file
 * Manage here all the pages which relate to CRUD functionallity.
 */

/**
 * Manage an app entity.
 */
function dc_apps_app_form($form, &$form_state, DrupalConnectApps $app = NULL) {
  if (!$app) {
    $app = dc_apps_create();
  }
  $form_state['#entity'] = $app;

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The name of the application.'),
    '#required' => TRUE,
    '#default_value' => $app->title,
  );

  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The description of the application'),
    '#default_value' => $app->description,
  );

  // Get the entities and sort them in alphabetical order.
  $entities = entity_get_info();

  ksort($entities);
  $ignored = dc_apps_ignored_apps();

  foreach ($entities as $name => $info) {
    if (in_array($name, $ignored)) {
      // This entity should be displayed to the app creator.
      continue;
    }

    $need_info = empty($app->need[$name]) ? array() : $app->need[$name];

    $form['need'][$name][$name . '_need'] = array(
      '#type' => 'checkbox',
      '#title' => $info['label'],
      '#default_value' => empty($need_info) ? FALSE : TRUE,
    );

    $form['need'][$name][$name . '_methods'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Actions'),
      '#options' => array(
        'get' => t('Get'),
        'post' => t('Post'),
        'delete' => t('Delete'),
        'update' => t('Update'),
      ),
      '#attributes' => array('class' => array('container-inline')),
      '#default_value' => !empty($need_info['methods']) ? $need_info['methods'] : array(),
      '#states' => array(
        'visible' => array(
          ':input[name="' . $name . '_need"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['need'][$name][$name . '_search'] = array(
      '#type' => 'select',
      '#title' => t('Search by'),
      '#description' => t('Select the field/property on which apps can make a search.'),
      '#options' => dc_apps_build_fields($name),
      '#default_value' => empty($need_info['search']) ? '' : $need_info['search'],
      '#states' => array(
        'visible' => array(
          ':input[name="' . $name . '_need"]' => array('checked' => TRUE),
          ':input[name="' . $name . '_methods[get]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['need'][$name][$name . '_operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#description' => t('What the operator you would like to apply?'),
      '#default_value' => empty($need_info['operator']) ? '' : $need_info['operator'],
      '#options' => array(
        '=' => '=',
        'CONTAINS' => t('Contains'),
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="' . $name . '_need"]' => array('checked' => TRUE),
          ':input[name="' . $name . '_methods[get]"]' => array('checked' => TRUE),
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
    '#markup' => $app->app_secret ? $app->app_secret : t('Need be generated'),
  );

  $form['oauth']['connect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Connect with'),
    '#description' => t('Is this is a "Connect with" application?'),
    '#default_value' => $app->connect_with,
  );

  $form['oauth']['site'] = array(
    '#type' => 'textfield',
    '#title' => t('Site'),
    '#description' => t('Fill in the site address. This will affect the signature and could affect the redirect of the user.'),
    '#default_value' => $app->app_site,
    '#states' => array(
      'visible' => array(
        ':input[name="connect"]' => array('checked' => TRUE),
      ),
    ),
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
  // App name should be only in english.
  if (preg_match('/[^A-Za-z0-9 ]/', $form_state['values']['title'])) {
    form_set_error('title', t('The name of the app should be only in english.'));
  }

  // When basic "Connect with" app don't need entities to search upon.
  if ($form_state['values']['connect']) {
    if (empty($form_state['values']['site'])) {
      // But she need a site.
      form_set_error('site', t('A "Connect with" app need a site address to be valid.'));
    }
  }
  else {
    // The app must user at least one entity.
    $entities = array_keys(entity_get_info());
    $entity_selected = FALSE;
    foreach ($entities as $entity) {
      if ($form_state['values'][$entity . '_need']) {
        $entity_selected = TRUE;
        break;
      }
    }

    if (!$entity_selected) {
      form_set_error('', t('A basic app must use at least one entity.'));
    }
  }

  field_attach_form_validate('dc_app', $form_state['#entity'], $form, $form_state);
}

/**
 * Submit handler.
 */
function dc_apps_app_form_submit($form, &$form_state) {
  $app = $form_state['#entity'];
  $values = $form_state['values'];

  // Star building information about entity.
  $entities = array_keys(entity_get_info());
  $need = array();

  foreach ($entities as $entity) {
    if (!isset($values[$entity . '_methods']) || !in_array(TRUE, $values[$entity . '_methods'])) {
      // We don't need to store information for not needed entities.
      continue;
    }

    $need[$entity] = array(
      'methods' => $values[$entity . '_methods'],
      'search' => $values[$entity . '_search'],
      'operator' => $values[$entity . '_operator'],
    );
  }

  // Building the entity object.
  $app->title = $values['title'];
  $app->description = $values['description'];
  $app->need = $need;
  $app->connect_with = $values['connect'];
  $app->uid = user_load_by_name($values['name'])->uid;
  $app->app_site = $values['site'];

  // Generating secret and public for the entity.
  if (!empty($app->is_new)) {
    $op = 'created';
    $app->generateKeyAndSecret();
  }
  else {
    $op = 'updated';
  }

  // Update/save the entity.
  $app->save();

  // Showing messages.
  $params = array(
    '@name' => $app->title,
    '@op' => $op,
  );
  drupal_set_message(t('The app @name has @op successful.', $params));

  if (!empty($app->need['user'])) {
    drupal_set_message(t('Your app need the user information. This could be achieved only when the user approve the app.'), 'warning');
  }

  // Display message and redirect the user back to .
  $form_state['redirect'] = 'admin/apps';
}

/**
 * Ask the user if he wan't to delete the app.
 */
function dc_apps_app_delete($form, &$form_state, DrupalConnectApps $app) {
  $form_state['#entity'] = $app;
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $app->title)),
    'admin/apps',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Deleting the app.
 */
function dc_apps_app_delete_submit($form, &$form_state) {
  // Delete.
  $form_state['#entity']->delete();

  // Show message.
  drupal_set_message(t('The app @name has deleted successfully', array('@name' => $form_state['#entity']->title)));

  // Redirect user.
  $form_state['redirect'] = 'admin/apps';
}

/**
 * Approving apps confirmation form.
 */
function dc_apps_app_approve($form, &$form_state, DrupalConnectApps $app) {
  $form_state['#entity'] = $app;
  $entity_needed = array_keys($app->need);

  $need = array();
  foreach ($entity_needed as $need_entity) {
    $info = entity_get_info($need_entity);
    $need[] = $info['label'];
  }

  return confirm_form($form,
    t('Are you sure you want to approve @title?', array('@title' => $app->title)),
    'admin/apps',
    t('This app access to the next entities: !entities', array('!entities' => theme('item_list', array('items' => $need)))),
    t('Approve'),
    t('Cancel')
  );
}

/**
 * Approving app.
 */
function dc_apps_app_approve_submit($form, &$form_state) {
  $app = $form_state['#entity'];
  $app->status = 1;
  $app->save();

  $form_state['redirect'] = 'admin/apps';
  drupal_set_message(t('The app @name has been approved successfully.', array('@name' => $app->title)));
}
