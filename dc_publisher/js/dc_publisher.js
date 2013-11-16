
(function ($) {

  Drupal.behaviors.nodeFieldsetSummaries = {
    attach: function (context,settings) {
      $(settings.dc_publisher_tabs).each(function(index, value) {
        $("#" + value).tabs();
      });
    }
  };

})(jQuery);
