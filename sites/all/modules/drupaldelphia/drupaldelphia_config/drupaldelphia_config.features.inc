<?php
/**
 * @file
 * drupaldelphia_config.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function drupaldelphia_config_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
