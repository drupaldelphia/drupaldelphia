<?php
/**
 * @file
 * cod_session_video.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_session_video_user_default_permissions() {
  $permissions = array();

  // Exported permission: create field_video.
  $permissions['create field_video'] = array(
    'name' => 'create field_video',
    'roles' => array(
      'content editor' => 'content editor',
      'session organizer' => 'session organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: edit field_video.
  $permissions['edit field_video'] = array(
    'name' => 'edit field_video',
    'roles' => array(
      'content editor' => 'content editor',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: edit own field_video.
  $permissions['edit own field_video'] = array(
    'name' => 'edit own field_video',
    'roles' => array(
      'content editor' => 'content editor',
      'session organizer' => 'session organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: view field_video.
  $permissions['view field_video'] = array(
    'name' => 'view field_video',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: view own field_video.
  $permissions['view own field_video'] = array(
    'name' => 'view own field_video',
    'roles' => array(
      'content editor' => 'content editor',
      'session organizer' => 'session organizer',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
