<?php
/**
 * @file
 * discogs_commerce.feeds_importer_default.inc
 */

/**
 * Implementation of hook_feeds_importer_default().
 */
function discogs_commerce_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'discogs_product_importer';
  $feeds_importer->config = array(
    'name' => 'Discogs Product Importer',
    'description' => 'Grab Discogs releases from JSON and turn them into products',
    'fetcher' => array(
      'plugin_key' => 'FeedsDiscogsFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
       'debug' => array(
        'options' => array(       
          'context' => 'context',
             'jsonpath_parser:0'   => 'id',
             'jsonpath_parser:1'   => 'title',
             'jsonpath_parser:2'   => 'labels[*].catno',
             'jsonpath_parser:3'   => 'country',
             'jsonpath_parser:4'   => 'formats[*].name',
             'jsonpath_parser:5'   => 'labels[*].catno',
             'jsonpath_parser:6'   => 'main_release',
             'jsonpath_parser:7'   => 'formats[*].qty',
             'jsonpath_parser:8'   => 'released',    
          ),
       'debug' => array(
        'options' => array(       
          'context' => 'context',
            'jsonpath_parser:0'    => 0,
            'jsonpath_parser:1'    => 0,
            'jsonpath_parser:2'    => 0,
            'jsonpath_parser:3'    => 0,
            'jsonpath_parser:4'    => 0,
            'jsonpath_parser:5'    => 0,
            'jsonpath_parser:6'    => 0,
            'jsonpath_parser:7'     => 0,
            'jsonpath_parser:8'     => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsCommerceProductProcessor',
      'config' => array(
        'product_type' => 'product',
        'author' => '1',
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'sku',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'field_catno',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_country',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'field_format',
            'unique' => FALSE,
          ),	 
         5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_label',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_main_release',
            'unique' => FALSE,
          ),	
          7 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_quantity',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'jsonpath_parser:8',
            'target' => 'field_released',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => NULL,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['discogs_product_importer'] = $feeds_importer;

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'discogs_product_reference_importer';
  $feeds_importer->config = array(
    'name' => 'Discogs Product Reference Importer',
    'description' => 'Pull the Discogs main release data in from JSON and make it into nodes',
    'fetcher' => array(
      'plugin_key' => 'FeedsDiscogsFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.resp.release',    
        'sources' => array(
             'jsonpath_parser:0'    =>  'id',
             'jsonpath_parser:1'    =>  'title',
             'jsonpath_parser:2'    =>  'id',
             'jsonpath_parser:3'    =>  'artists[*].name',
             'jsonpath_parser:4'    =>  'images[*].uri150[0]',
             'jsonpath_parser:5'    =>  'formats[*].descriptions[*]',
             'jsonpath_parser:6'    =>  'notes',
             'jsonpath_parser:7'    =>  'year',
          ),      
       'debug' => array(
        'options' => array(       
          'context' => 'context',
            'jsonpath_parser:0'   => 0,
            'jsonpath_parser:1'   => 0,
            'jsonpath_parser:2'   => 0,
            'jsonpath_parser:3'   => 0,
            'jsonpath_parser:4'   => 0,
            'jsonpath_parser:5'   => 0,
            'jsonpath_parser:6'   => 0,
            'jsonpath_parser:7'   => 0,
          ),
        ),          
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'master_release',
        'expire' => '-1',
        'author' => '1',
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' =>  'jsonpath_parser:1',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'field_product:sku',
            'unique' => FALSE,
          ),
        3 => array(
          'source' => 'jsonpath_parser:3',
          'target' => 'field_artist',
          'unique' => FALSE,
        ),
       4 => array(
          'source' => 'jsonpath_parser:4',
          'target' => 'field_img',
          'unique' => FALSE,
        ),
       5 => array(
          'source' => 'jsonpath_parser:5',
          'target' => 'field_items',
          'unique' => FALSE,
        ),
       6 => array(
          'source' => 'jsonpath_parser:6',
          'target' => 'field_notes',
          'unique' => FALSE,
          7 => array(
          'source' => 'jsonpath_parser:7',
          'target' => 'field_year',
          'unique' => FALSE,
        ),
        ),
        'update_existing' => '1',
        'input_format' => 'full_html',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['discogs_product_reference_importer'] = $feeds_importer;

  return $export;
}
