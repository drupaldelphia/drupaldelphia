<?php
/**
 * @file
 * CartAddSponsorshipForm.inc
 *
 * This defines a handler for our alterations to our commerce_add_to_cart
 * process.
 */

module_load_include('inc', 'cod_sponsor_sales', 'includes/EntityForm');

class CartAddSponsorshipForm extends EntityForm {
  protected $sponsorSales;
  protected $sponsorProducts;
  public $isSponsorshipProduct;

  /**
   * Constructor for SponsorSalesForm.
   */
  public function __construct(&$form) {
    parent::__construct($form);
    $this->sponsorSales = new SponsorSales();
    $this->sponsorProducts = $this->sponsorSales->getSponsorProducts();

    // We need this object during the submit process.
    $this->form['#cart_add_form'] = $this;
    $this->isSponsorshipProduct = $this->isSponsorshipProduct();
  }

  /**
   * Checks that the form is set to add a sponsorship.
   */
  public function isSponsorshipProduct() {
  }

  /**
   * Instead of adding adding directly to cart detur to the Sponsor add form.
   */
  public function overrideDefaultSubmit() {
  }

  /**
   * Redirect to Sponsor add form.
   *
   * Checks whether there already is a sponsorship in the cart and redirect
   * either to the Sponsor node form already started or to a new one.
   */
  public function goToSponsorNodeAdd() {
  }
}
