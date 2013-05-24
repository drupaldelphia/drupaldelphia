<?php
/**
 * @file
 * cod_sponsor_sales.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cod_sponsor_sales_default_rules_configuration() {
  $items = array();
  $items['rules_create_new_sponsorship_display_for_sponsorship_product'] = entity_import('rules_config', '{ "rules_create_new_sponsorship_display_for_sponsorship_product" : {
      "LABEL" : "Create new Sponsorship Display for Sponsorship Product",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : [ "commerce_product_insert" ],
      "IF" : [
        { "entity_has_field" : {
            "entity" : [ "commerce-product" ],
            "field" : "field_sponsor_sponsorship_level"
          }
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "sponsorship_display",
              "param_title" : "[commerce-product:title]",
              "param_author" : [ "commerce-product:creator" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-sponsor-sponsorship-level" ],
            "value" : [ "commerce-product:field-sponsor-sponsorship-level" ]
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-product-id" ],
            "value" : [ "commerce-product" ]
          }
        }
      ]
    }
  }');
  return $items;
}
