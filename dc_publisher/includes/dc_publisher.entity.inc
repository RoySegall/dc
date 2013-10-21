<?php
/**
 * @file
 * Holds the basic structure of the entity.
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
}
