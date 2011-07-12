<?php
/**
 * @file
 * discogs_commerce.features.inc
 */
 
/**
 * Implementation of hook_ctools_plugin_api().
 */
function discogs_commerce_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function discogs_commerce_node_info() {
  $items = array(
    'master_release' => array(
      'name' => t('Discography Commerce masterRelease'),
      'base' => 'node_content',
      'description' => t('Discography commerce content type. Holds the information for Discography Commerce masterRelease.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_commerce_product_default_types().
*/
function discogs_commerce_commerce_product_default_types(){
  $items = array(
      array(
      'type' => 'release',
      'name' => t('Discography Release'),
      'description' => t('Discography Release (product type).'),
      'help' => '',      
      ),
  );
  return $items;
}