<?php
/**
 * @file
 * SponsorshipLevelVocabulary.inc
 *
 * Extends the Vocabulary class to define Sponsorship Level vocabulary specific
 * data and behavior.
 */

module_load_include('inc', 'cod_sponsor_sales', 'includes/Vocabulary');

class SponsorshipLevelVocabulary extends Vocabulary {

  protected $sponsorSales;

  /**
   * Constructor for SponsorLevel Vocabulary.
   */
  public function __construct() {
    parent::__construct('sponsorship_level');
    $this->sponsorSales = new SponsorSales();
  }

  /**
   * Tries to create a new  sponsorship products from sponsorship level terms.
   *
   * This method will verify that $term belongs to the sponsorship_level
   * vocabulary.  If so it retrieves a new sponsorship product but does not save
   * it unless the product is unique.  In the case that the product is not
   * unique, the $term is deleted from the sponsorship vocabulary because it
   * does not make sense to have non unique sponsorship levels.
   *
   * @param Entity $term
   *   A term entity as supplied by hook_taxonomy_term_insert.
   *
   * @return Bool
   *   Returns whether or not product creation was successful.   
   */
  public function addSponsorshipProduct($term) {
    if ($this->isSponsorshipLevel($term)) {

      $sponsorship = $this->buildSponsorshipProduct($term);

      if ($product = commerce_product_load_by_sku($sponsorship->sku)) {
        $tid = $product->field_sponsor_sponsorship_level[LANGUAGE_NONE][0]['tid'];
        // Do not delete term if it shares the same tid with the product.
        if ($tid != $term->tid) {
          taxonomy_term_delete($term->tid);
        }
        return FALSE;
      }
      else {
        commerce_product_save($sponsorship);
        $this->sponsorSales->setProduct($sponsorship->product_id);
        return TRUE;
      }
    }
  }

  /**
   * Determine if the $term belongs to the sponsorship_level vocabulary.
   */
  protected function isSponsorshipLevel($term) {
    $vid = $this->getID();
    return ($vid == $term->vid);
  }

  /**
   * Builds new sponsorship product using the $term and returns it.
   */
  protected function buildSponsorshipProduct($term) {
    $sponsorship = commerce_product_new('commerce_node_checkout');
    $sponsorship->sku = $term->name . '-' . $this->sponsorSales->getDefaultSku();
    $sponsorship->title = $term->name . ' Sponsorship';
    $sponsorship->uid = 1;
    $sponsorship->field_sponsor_sponsorship_level[LANGUAGE_NONE][0]['tid'] = $term->tid;

    $price = variable_get("cod_sponsorship_{$term->name}_price", 65000);
    $code = variable_get("cod_sponsorship_{$term->name}_currency", 'USD');
    $sponsorship->commerce_price[LANGUAGE_NONE][0]['amount'] = $price;
    $sponsorship->commerce_price[LANGUAGE_NONE][0]['currency_code'] = $code;

    return $sponsorship;
  }

  /**
   * Tries to delete the corresponding sponsorship product for the term given.
   *
   * This method will verify that $term belongs to the sponsorship_level
   * vocabulary.  If so it loads an associated  sponsorship product and if
   * successful, deletes that product as well as any database variables options
   * set for the product.
   *
   * @param Entity $term
   *   A term entity as supplied by hook_taxonomy_term_insert.
   *
   * @return Bool
   *   Returns whether or not product deletion was successful.   
   */
  public function deleteSponsorshipProduct($term) {
    if ($this->isSponsorshipLevel($term)) {

      $product_id = $this->getSponsorshipProductId($term);

      if ($product_id) {
        $this->sponsorSales->unsetProduct($product_id);
        return commerce_product_delete($product_id);
      }
    }
    return FALSE;
  }

  /**
   * Retrieves a sponsorship product_id based on the term.
   */
  protected function getSponsorshipProductId($term) {
    if (is_numeric($term)) {
      $tid = $term;
    }
    elseif (is_object($term) && isset($term->tid)) {
      $tid = $term->tid;
    }

    $tid = (int) $tid;

    $product_id = db_select('field_data_field_sponsor_sponsorship_level', 's_l')
      ->fields('s_l', array('entity_id'))
      ->condition('s_l.field_sponsor_sponsorship_level_tid', $tid, '=')
      ->condition('s_l.entity_type', 'commerce_product', '=')
      ->condition('s_l.bundle', 'commerce_node_checkout', '=')
      ->execute()
      ->fetchField();

    return $product_id;

  }
}
