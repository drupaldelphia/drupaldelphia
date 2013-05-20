<?php
/**
 * @file
 * Vocabulary.inc
 *
 * Defines a base wrapper class for drupal taxonomy vocabulary object and
 * methods.
 */

abstract class Vocabulary {

  protected $vocabulary;

  /**
   * Vocabulary object consturctor.
   */
  public function __construct($vocabulary) {
    $names = taxonomy_vocabulary_get_names();

    if (is_object($vocabulary && isset($vocabulary->vid))) {
      $this->vocabulary = $vocabulary;
    }
    elseif (is_int($vocabulary)) {
      $this->vocabulary = taxonomy_vocabulary_load($vocabulary);
    }
    elseif (is_string($vocabulary) && isset($names[$vocabulary])) {
      $this->vocabulary = taxonomy_vocabulary_load($names[$vocabulary]->vid);
    }
    else {
      $this->vocabulary = FALSE;
    }

  }

  /**
   * Returns the vocabulary machine name.
   */
  public function getMachineName() {
    return $this->vocabulary->machine_name;
  }

  /**
   * Returns the vocabulary name.
   */
  public function getName() {
    return $this->vocabulary->name;
  }

  /**
   * Rerturns the vocabulary id.
   */
  public function getID() {
    return $this->vocabulary->vid;
  }

  /**
   * Returns the vocabulary data-structure.
   */
  public function getVocabulary() {
    return $this->vocabulary;
  }
}
