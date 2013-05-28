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

  /**
   * Constructor for SponsorSalesForm.
   */
  public function __construct(&$form, &$form_state) {
    parent::__construct($form);
    $this->form_state =& $form_state;
    $this->sponsorSales = new SponsorSales();
    $this->sponsorProducts = $this->sponsorSales->getSponsorProducts();

    // We need this object during the submit process.
    $this->form['#cart_add_form'] = $this;
  }

  /**
   * Checks that the form is set to add a sponsorship.
   */
  public function isSponsorshipProduct() {
    return in_array($this->form['product_id']['#value'],
      $this->sponsorProducts);
  }

  /**
   * Instead of adding directly to cart detur to the Sponsor add form.
   */
  public function overrideDefaultSubmit() {
    $this->form['#submit'] = array('cod_sponsor_sales_add_to_cart_submit');
  }

  /**
   * Redirect to Sponsor add form.
   */
  public function goToSponsorNodeAdd() {
    $this->form_state['redirect'] = array(
      'node/add/sponsor',
      array(
        'query' => array(
          'tid' => $this->getSponsorLevel(),
        ),
      ),
    );
  }

  /**
   * Returns the sponsor level for the sponsorship associted with this form.
   */
  public function getSponsorLevel() {
    return $this->form_state['default_product']
      ->field_sponsor_sponsorship_level[LANGUAGE_NONE][0]['tid'];
  }
}
