/**
 * @file
 * A JavaScript file for the theme.
 *
 */

(function($) {
  Drupal.behaviors.drupaldelphia = {
    attach: function(context, settings) {
      $('.mobile-handle').click(function() {
        $('body').toggleClass('slide');
      });
      $('select')
        .wrap('<div class="input-wrap" />')
        .after('<span class="select" />');
    }
  };
})(jQuery);