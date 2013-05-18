<?php
/**
 * @file
 * SponsorSalesForm.inc
 *
 * Define the SponsorSalesForm class that holds the logic sourrounding the form
 * alter behavior for the sponsor sales feature.
 */


class SponsorSalesForm extends EntityForm {
  protected $node;
  protected $sponsorSales;
  protected $sponsorProducts;

  /**
   * Constructor for SonsorSalesForm.
   */
  public function __construct(&$form) {
    parent::__construct($form);
    $this->node =& $this->form['#node'];
    $this->sponsorSales = new SponsorSales();
    $this->enabledProducts = $this->sponsorSales->getSponsorProducts();
  }

  /**
   * Determine whether to alter the Sponsor Node add form.
   */
  public function isReady() {
    // We need to adhere to the same conditions as the commerce_node_checkout
    // module.
    return (!empty($enabled_products)
      && !user_access('administer nodes')
      && $this->node->status == 0
      && empty($this->node->nid));
  }

  /**
   * Gets the sponsorship item and adds it to the form. 
   */
  public function addDynamicSponsorshipItem() {
    $checkout_product = $this->getCheckoutProduct();
    $this->form['commerce_node_checkout_product'] = $checkout_product;
  }

  /**
   * Determine the taxonomy based on the sponsor level taxonomy.
   */
  protected function getCheckoutProduct() {
    $form['commerce_node_checkout_product'] = array(
      '#type' => 'value',
      '#value' => array_shift(array_keys($products)),
    );
    $product = array();
    return $product();
  }

  /**
   * Redirect the user to the checkout form on sponsor node insert.
   */
  public function addCheckoutRedirect() {
    $this->form['actions']['submit']['#submit'][]
      = 'commerce_node_checkout_node_insert_redirect';
  }
}
