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
    $this->sponsorProducts = $this->sponsorSales->getSponsorProducts();
  }

  /**
   * Determine whether to alter the Sponsor Node add form.
   */
  public function isReady() {
    // We need to adhere to the same conditions as commerce_node_checkout.
    $check = (!empty($this->sponsorProducts)
      && !user_access('administer nodes')
      && $this->node->status == 0
      && empty($this->node->nid));
    return $check;
  }

  /**
   * Gets the sponsorship item and adds it to the form. 
   *
   * We are doing this essentially to override the default
   * commerce_node_checkout form alteration.
   */
  public function addDefaultSponsorshipItem() {
    $checkout_product = $this->sponsorSales->getDefaultProduct();
    $item = array(
      '#type' => 'value',
      '#value' => $checkout_product->product_id,
    );
    $this->form['commerce_node_checkout_product'] = $item;
  }

  /**
   * Addd the sponsorship prodcut callback.
   */
  public function addSponsorshipActionCallback() {
    $callback = 'sponsor_sales_add_sponsorship';
    $submit =&  $this->form['actions']['submit']['#submit'];
    array_unshift($submit, $callback);
  }
}
