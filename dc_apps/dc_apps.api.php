<?php

/**
 * @file
 * Describing the hooks available via Drupal apps connect module.
 */

/**
 * Implements hook_dc_apps_generate_links_action_alter().
 *
 * Each Drupal connect apps entity has a method for generate links. The method
 * is helpful when we want to create a link relate to action we need apply on
 * the entity: editing, deleting or watching the documentation of the app.
 *
 * When other module want to add a new action and want to use the method for
 * generating the link for the action they should use these hook.
 *
 * Using the generateLink methods will be similar like this:
 *  $app = dc_apps_load(1);
 *  $link = $app->generateLink('new_methods');
 */
function hook_dc_apps_generate_links_action_alter(&$actions) {
  $actions = array(
    'new_action' => array(
      'title' => t('New action'),
      'href' => 'admin/apps/' . $this->id . '/new_action',
    ),
  );
}
