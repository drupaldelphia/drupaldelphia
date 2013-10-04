<?php
/**
 * @file
 * Available variables:
 */
?>

<div class="splash-area">
  <div class="clearfix">
    <h2><?php print t('Philadelphia'); ?></h2>
  </div>
  <div class="clearfix">
    <h3 class="ribbon">
      <?php print t('October 11, 2013'); ?>
      <i></i>
      <i></i>
      <i></i>
      <i></i>
    </h3>
  </div>
  <div class="clearfix">
    <?php print l(t('Buy a Ticket'), 'buy-ticket', array('attributes' => array('class' => array('btn')))); ?>
    <?php print l(t('View Sessions'), 'sessions', array('attributes' => array('class' => array('btn')))); ?>
  </div>
</div>

