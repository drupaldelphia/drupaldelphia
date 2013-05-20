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
  /**
   * Constructor for SponsorLevel Vocabulary.
   */
  public function __construct() {
    parent::__construct('sponsorship_level');
  }
}
