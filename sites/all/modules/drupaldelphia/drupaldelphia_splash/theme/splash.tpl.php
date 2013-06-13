<?php

/**
 * @file
 * Available variables:
 */

?>

<div class="splash-area">
  <h2><?php print t('Philadelphia'); ?></h2>

  <h3 class="ribbon">
    <?php print t('October 1st, 2013'); ?>
    <i></i>
    <i></i>
    <i></i>
    <i></i>
  </h3>

  <div>
    <?php print l(t('Buy a Ticket'), 'content/drupaldelphia-2013', array('attributes' => array('class' => array('btn')))); ?>
    <?php print l(t('Submit a Session'), 'node/add/session', array('attributes' => array('class' => array('btn')))); ?>
  </div>
</div>

