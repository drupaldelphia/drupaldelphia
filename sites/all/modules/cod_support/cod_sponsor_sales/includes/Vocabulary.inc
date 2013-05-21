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

  /**
   * Saves a term to this vocabulary.
   *
   * @param Mixed $name
   *   Can be either a string, in which a new $term instance is created
   *   or can be a $term instance.
   */
  public function saveTerm($name) {
    if (is_object($name) && isset($name->vid)) {
      $term = $name;
    }
    else {
      $term = $this->buildTerm($name);
    }

    return taxonomy_term_save($term);
  }

  /**
   * Alias for saveTerm() method.
   */
  public function addTerm($term) {
    return $this->saveTerm($term);
  }

  /**
   * Remove a term from this vocabulary.
   *
   * @param Mixed $name
   *   Can be either a string, in which a new $term instance is created
   *   or can be a $term instance, or can be a term id.
   */
  public function deleteTerm($name) {
    if (is_object($name) && isset($name->tid)) {
      $term = $name;
    }
    elseif (is_numeric($name)) {
      $term = new StdClass();
      $term->tid = (int) $name;
    }
    else {
      // Assumes term is unique by design.
      $machine_name = $this->getMachineName();
      $term = taxonomy_get_term_by_name($name, $machine_name);
      $term = array_pop($term);
    }

    if ($term) {
      return taxonomy_term_delete($term->tid);
    }

    return FALSE;
  }

  /**
   * Builds and returns a sponsorship level term.
   */
  protected function buildTerm($name) {
    $term = new StdClass();
    $term->vid = $this->getID();
    $term->name = $name;
    $term->machine_name = $this->getMachineName();

    return $term;
  }
}
