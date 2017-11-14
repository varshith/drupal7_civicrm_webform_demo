<?php
/**
 * Created by PhpStorm.
 * User: varshith
 * Date: 4/11/17
 * Time: 8:51 PM
 */

/**
 * @file
 * Plugin to check if the title has configured string.
 */

$plugin = array(
    'title' => t('User Profile Status'),
    'description' => t('Checks if the user profile is completed.'),
    'callback' => 'user_profile_status_access_check',
    'default' => array('negate' => 0),
    'summary' => 'user_profile_status_access_summary',
    'settings form' => 'user_profile_status_access_settings',
);

/**
 * Settings form for the 'user profile status' access plugin.
 */
function user_profile_status_access_settings($form, &$form_state, $conf) {
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
 * Provide a summary description.
 */
function user_profile_status_access_summary($conf, $context) {
    $replacement = array('@webform' => $conf['webform_id']);
    return t('Checks if current user has updated their profile form(@webform).', $replacement);
}

/**
 * Check for access.
 */
function user_profile_status_access_check($conf, $context) {
    global $user;
    if($user->uid == 0) {
        return FALSE;
    }
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    if (webform_get_submission_count($conf['webform_id'], $user->uid) > 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
