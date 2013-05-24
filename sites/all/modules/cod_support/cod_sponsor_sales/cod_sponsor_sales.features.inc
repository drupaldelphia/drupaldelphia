<?php
/**
 * @file
 * cod_sponsor_sales.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_sponsor_sales_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cod_sponsor_sales_node_info() {
  $items = array(
    'sponsorship_display' => array(
      'name' => t('Sponsorship Sales Display'),
      'base' => 'node_content',
      'description' => t('Sponsorship Sales Product Display Content Type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
