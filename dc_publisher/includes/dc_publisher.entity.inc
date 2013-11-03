<?php
/**
 * @file
 * Holds the basic structure of the entity.
 */

/**
 * Class DrupalPublisherApprovedApp extends Entity
 *
 * Holding the object for Drupal publisher approved app.
 */
class DrupalPublisherApprovedApp extends Entity {

  /**
   * @var
   * The identifier.
   */
  public $id;

  /**
   * @var
   * The primary identifier for a applications.
   */
  public $app_id;

  /**
   * @var
   * The {users}.uid that owns this application.
   */
  public $uid;

  /**
   * @var
   * The Unix timestamp when the entry was created.
   */
  public $timestamp;

  /**
   * @var
   * The status of the app - disabled, enabled.
   */
  public $status;

  /**
   * Get the application object.
   *
   * @return DrupalConnectApps
   *  The application object.
   */
  function app() {
    if (!$this->app_id) {
      return;
    }

    return dc_apps_load($this->app_id);
  }
}

/**
 * Class DrupalPublisherAuthorizedSession extends Entity
 *
 * Holds the object of the Drupal publisher authorized session.
 */
class DrupalPublisherAuthorizedSession extends Entity {
  /**
   * @var
   * The identifier.
   */
  public $id;

  /**
   * @var
   * The primary identifier for a applications.
   */
  public $app_id;

  /**
   * @var
   * The session string.
   */
  public $session;

  /**
   * @var
   * The Unix timestamp when the entry was created.
   */
  public $timestamp;
}
