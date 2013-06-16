/**
 * @file
 * A JavaScript file for the theme.
 *
 */

(function($) {
  Drupal.behaviors.drupaldelphia = {
    attach: function(context, settings) {
      // Adds Classes to body and mobile-handle when clicked.
      $(function() {
        $('.mobile-handle').click(function() {
          $('body').toggleClass('slide');
          $(this).toggleClass('on');
        });
      });
      $('select')
        .wrap('<div class="input-wrap" />')
        .after('<span class="select" />');
      // Makes nav bar stick to top when scrolling
      function sticky_relocate() {
        var window_top = $(window).scrollTop();
        if ($('#navbar-administration').length) {
          $('body').addClass('nav-stick');
          window_top += 39;
        }
        var logo_top = $('#header').offset().top;
        logo_top += 56;
        if (window_top > logo_top) {
          $('.header-inner').addClass('stick');
        } else {
          $('.header-inner').removeClass('stick');
        }
      }
      $(function() {
        $(window).scroll(sticky_relocate);
        sticky_relocate();
      });
    }
  };
})(jQuery);
