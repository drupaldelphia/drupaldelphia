<?php
/**
 * @file
 * SponsorSales.inc
 *
 * A class to hold Sponsor Sales logic.
 */

class SponsorSales {

  protected $permissions = array(
    'create sponsor content',
    'access checkout',
  );

  /**
   * Adds a default sponsorship product to cod.
   */
  public function addDefaultProduct() {
    if (!commerce_product_load_by_sku('sponsorship')) {
      $sponsorship = commerce_product_new('commerce_node_checkout');
      $sponsorship->sku = 'SPONSORSHIP';
      $sponsorship->title = 'Sponsorship';
      $sponsorship->uid = 1;

      $price = variable_get('cod_sponsorship_default_price', 650);
      $code = variable_get('cod_sponsorship_default_currency', 'USD');
      $sponsorship->commerce_price[LANGUAGE_NONE][0]['amount'] = $price;
      $sponsorship->commerce_price[LANGUAGE_NONE][0]['currency_code'] = $code;

      commerce_product_save($sponsorship);
    }
  }

  /**
   * Grants the permission required for using this module.
   */
  public function grantPerms($roles = array(DRUPAL_AUTHENTICATED_RID)) {
    foreach ($roles as $rid) {
      user_role_grant_permissions($rid, $this->permissions);
    }
  }

}
