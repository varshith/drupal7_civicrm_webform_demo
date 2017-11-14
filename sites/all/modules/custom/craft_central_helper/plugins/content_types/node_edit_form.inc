<?php
/**
 * Created by PhpStorm.
 * User: varshith
 * Date: 4/11/17
 * Time: 9:40 PM
 */

$plugin = array(
    'single' => TRUE,
    'title' => t('Profile Edit'),
    'category' => t('Craft Central panes'),
    'edit form' => 'node_edit_settings_form',
    'render callback' => 'node_edit_form_render',
    'all contexts' => TRUE,
);

function node_edit_settings_form($form, $form_state, $conf) {
    $conf = $form_state['conf'];
    $nodes = node_load_multiple(array(), array(
        'type' => 'webform',
        'status' => 1,
    ));
    $webforms = array();
    foreach ($nodes as $nid => $node) {
        $webforms[$nid] = check_plain($node->title);
    }
    $form['settings']['webform_id'] = array(
        '#type' => 'select',
        '#title' => t('Select Profile Webform'),
        '#description' => t('Select the webform which is used for user profile.'),
        '#options' => $webforms,
        '#default_value' => $conf['webform_id'],
    );
    return $form;
}

/**
 * Ctools edit form submit handler.
 *
 * @param $form
 * @param $form_state
 */
function node_edit_settings_form_submit($form, &$form_state) {
    foreach (array('webform_id') as $key) {
        $form_state['conf'][$key] = $form_state['values'][$key];
    }
}

function node_edit_form_render($subtype, array $conf = array(), $args, $context) {
    global $user;
    // Render as a block.
    $block = new stdClass();
    $block->module = 'craft_central_helper';
    if(isset($conf['webform_id']) && is_numeric($conf['webform_id'])) {
        $node = node_load($conf['webform_id']);
        module_load_include('inc', 'webform', 'includes/webform.submissions');
        $submissions = webform_get_submissions(array('nid' => $node->nid, 'uid' => $user->uid));
        $submission = reset($submissions);
        $c = drupal_get_form('webform_client_form_' . $node->nid, $node, $submission);
        $block->content = $c;
    }
    else {
        $block->content = '';
    }
    return $block;
}