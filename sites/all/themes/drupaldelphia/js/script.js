/**
 * @file
 * A JavaScript file for the theme.
 *
 */

(function($) {
  Drupal.behaviors.drupaldelphia = {
    attach: function(context, settings) {
      $('.handle').click(function() {
        $('body').toggleClass('slide');
      });
    }
  };
})(jQuery);