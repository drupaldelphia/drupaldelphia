<?php
/**
 * @file
 * SponsorSales.inc
 *
 * A class to hold Sponsor Sales logic.
 */

class SponsorSales {

  protected $nodeType = 'sponsor';
  protected $defaultSku = 'SPONSORSHIP';
  protected $permissions = array(
    'create sponsor content',
    'access checkout',
  );

  /**
   * Sets a default sponsorship product to cod.
   */
  public function setDefaultProduct() {
    $sponsorship = $this->getDefaultProduct();
    if (!$sponsorship) {
      $sponsorship = $this->buildDefaultProduct();
      commerce_product_save($sponsorship);
    }
    $this->setProduct($sponsorship->product_id);
  }

  /**
   * Gets the default sponsorship product.
   */
  public function getDefaultProduct() {
    $sku = $this->defaultSku;
    $sponsorship = commerce_product_load_by_sku($sku);
    return $sponsorship;
  }

  /**
   * Builds a default sponsorship product.
   */
  public function buildDefaultProduct() {
    $sponsorship = commerce_product_new('commerce_node_checkout');
    $sponsorship->sku = $this->defaultSku;
    $sponsorship->title = 'Sponsorship';
    $sponsorship->uid = 1;

    $price = variable_get('cod_sponsorship_default_price', 650);
    $code = variable_get('cod_sponsorship_default_currency', 'USD');
    $sponsorship->commerce_price[LANGUAGE_NONE][0]['amount'] = $price;
    $sponsorship->commerce_price[LANGUAGE_NONE][0]['currency_code'] = $code;

    return $sponsorship;
  }

  /**
   * Associate a product with the sponsor node type.
   */
  public function setProduct($product_id) {
    (int) $product_id;
    $products = (array) $this->getSponsorProducts();
    if (!in_array($product_id, $products)) {
      $products[] = $product_id;
    }
    variable_set('commerce_node_checkout_products_sponsor', $products);
  }

  /**
   * Returns the db variable for the sponsor commerce_node_checkout product.
   */
  public function getSponsorProducts() {
    $type = $this->nodeType;
    $products = commerce_node_checkout_get_products_by_type($type);
    return $products;
  }

  /**
   * Grants the permission required for using this module.
   */
  public function grantPerms($roles = array(DRUPAL_AUTHENTICATED_RID)) {
    foreach ($roles as $rid) {
      user_role_grant_permissions($rid, $this->permissions);
    }
  }

  /**
   * Makes sure these hooks run after commerce_node_checkout.
   */
  public function initiateModuleWeight() {
    $weight_cnc = db_query("select weight from system where name = 'commerce_node_checkout'")->fetchField();
    $weight = $weight_cnc + 1;

    db_update('system')
      ->fields(array('weight' => $weight))
      ->condition('type', 'module')
      ->condition('name', 'cod_sponsor_sales')
      ->execute();
  }
}
