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
   * Generate key and secret keys for a new application.
   *
   * @TODO: Find a way how?!
   */
  public function generateKeyAndSecret() {
  }
}
