<?php

class DrupalConnectApps extends Entity {

  /**
   * @var
   * The primary identifier for a applications.
   */
  public $id;

  /**
   * @var
   * The title of this application.
   */
  public $title;

  /**
   * @var
   * A description of the application.
   */
  public $description;

  /**
   * @var
   * The unix time stamp the app was created.
   */
  public $time;

  /**
   * @var
   * The {users}.uid that owns this application.
   */
  public $uid;

  /**
   * @var
   * The status of the app.
   */
  public $status;

  /**
   * @var
   * The entity types from which the app will fetch the data.
   */
  public $need;

  /**
   * @var
   * The key of the app.
   */
  public $app_key;

  /**
   * @var
   * The secret of the app.
   */
  public $app_secret;

  /**
   * @var
   * The site address which the data will be pulled from.
   */
  public $app_site;

  /**
   * Overrides save().
   */
  public function save() {
    // Before saving verify the user did not changed the key and secret keys.
    parent::save();
  }

  /**
   * Generating links of the app.
   *
   * @param $action
   *  The type of the actions: edit, delete or documentation.
   * @param $account
   *  The account user. This will take care of permissions.
   *
   * @return String
   *  The link for the action.
   */
  public function generateLink($action, $account = NULL) {
    $actions = array(
      'edit' => array(
        'title' => t('Edit'),
        'href' => 'admin/apps/' . $this->id . '/edit',
      ),
      'delete' => array(
        'title' => t('Delete'),
        'href' => 'admin/apps/' . $this->id . '/delete',
      ),
    );

    drupal_alter('dc_apps_generate_links_action_alter', $actions);

    $item = menu_get_item($actions[$action]['href']);

    if (!$item['access']) {
      return;
    }

    return l($actions[$action]['title'], $actions[$action]['href']);
  }

  /**
   * Generate key and secret keys for a new application.
   */
  public function generateKeyAndSecret() {
    $user = user_load($this->uid);

    $this->app_key = str_replace(array(' ', '', '-'), '_', strtolower($this->title));
    $this->app_secret = md5($user->name . $this->time);
  }
}
