/**
 * Created by varshith on 12/11/17.
 */
(function($) {
    jQuery(document).ready(function($) {
        var i = 0;
        $('.product-gallery').each(function() {
            if(i == 0) {
                i++;
            }
            else {
                if($(this).find('.form-item input.form-text').val() == '')
                    $(this).hide();
                else
                    i++;
            }
        });
        insertAddMoreButtonAfter('.webform-component--civicrm-2-contact-'+i+'-cg3-fieldset');
        $('.pane-content form').on('click', '.addMore', function() {
            i++;
            $(this).remove();
            if($('.webform-component--civicrm-2-contact-'+i+'-cg3-fieldset').length) {
                $('.webform-component--civicrm-2-contact-'+i+'-cg3-fieldset').show('fast');
                insertAddMoreButtonAfter('.webform-component--civicrm-2-contact-'+i+'-cg3-fieldset');
            }
        });
    });
    function insertAddMoreButtonAfter(selector) {
        $('<button class="btn btn-info addMore pull-right">Add more</button>').insertAfter(selector);
    }
})(jQuery);
