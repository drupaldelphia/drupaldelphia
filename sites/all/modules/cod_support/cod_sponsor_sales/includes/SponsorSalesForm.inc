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
   * Constructor for SponsorSalesForm.
   */
  public function __construct(&$form) {
    parent::__construct($form);
    $this->node =& $this->form['#node'];
    $this->sponsorSales = new SponsorSales();
    $this->sponsorProducts = $this->sponsorSales->getSponsorProducts();

    // We need this object during the submit process.
    $this->form['#sponsorship_sales'] = $this;
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
   * Makes the sponsor level option not required when no options are available.
   */
  public function unrequireSponsorLevel() {
    if (!$this->hasSponsorLevelOptions()) {
      $this->setElementPropertyValue('field_sponsor_sponsorship_level',
        '#required', FALSE);
    }
  }

  /**
   * Checks to see if the sponsor form has sponsor level options.
   */
  public function hasSponsorLevelOptions() {
    $field = $this->getElement('field_sponsor_sponsorship_level');
    return !(count($field['#options']) == 1 && isset($field['#options']['_none']));
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
   * Add the sponsorship product callback.
   */
  public function addSponsorshipActionCallback() {
    $callback = 'sponsor_sales_add_sponsorship';
    $submit =&  $this->form['actions']['submit']['#submit'];
    array_unshift($submit, $callback);
  }

  /**
   * Determines and adds  appropriate sponsorship value based on taxonomy level.
   *
   * This function will be invoked via the sponsorship_sales_add_sponsorship
   * callback function.
   */
  public function addSponsorshipValue(&$form_state) {
    $sponsor_level = $form_state['values']['field_sponsor_sponsorship_level'];
    $product_id = $this->sponsorSales->getSponsorProduct($sponsor_level);

    if ($product_id) {
      $form_state['values']['commerce_node_checkout_product'] = $product_id;
    }
  }
}
