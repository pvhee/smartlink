<?php

/**
 * Render a smartlink calculate form on node/id/smartlink_calculate pages.
 */
function smartlink_calculate_tab_form(&$form_state, $node) {
  //$importer_id = feeds_get_importer_id($node->type);

  $form = array();
  $form['#smartlink_nid'] = $node->nid;
  //$form['#importer_id'] = $importer_id;
  $form['#redirect'] = 'node/'. $node->nid;
  return confirm_form($form, t('Calculate smartlink for all users?'), 'node/'. $node->nid, '', t('Calculate'), t('Cancel'), 'confirm smartlink calculate');
}

/**
 * Submit handler for feeds_import_tab_form().
 */
function smartlink_calculate_tab_form_submit($form, &$form_state) {
  $form_state['redirect'] = $form['#redirect'];
  smartlink_batch_set($form['#smartlink_nid']);
}

///**
// * Render a smartlink calculate form on node/id/smartlink_calculate pages.
// */
//function smartlink_apply_form($type, $smartlink_node, $user) {
//  module_load_include('inc', 'node', 'node.pages');
//
//  /**
// * Presents a node editing or adding form for the given content profile.
// */
//  //drupal_set_title(check_plain($user->name));
//  $node = content_profile_load($type, $user->uid);
//  if (!$node) {
//    $node = array('uid' => $user->uid, 'name' => (isset($user->name) ? $user->name : ''), 'type' => $type, 'language' => '');
//  }
//  return drupal_get_form($type .'_node_form', $node);
//}

/**
 * Render a smartlink application form
 */
function smartlink_apply_form($smartlink_node, $user, $type = NULL) {
  $data = smartlink_get_data_user($user, $smartlink_node);

  if (!isset($type)) {
    // Find first incomplete field to determine the node edit form
    foreach ($data['fields'] as $i => $field) {
      if (!$field['completed']) {
        $type = $field['type_name'];
        break;
      }
    }
  }

  if (isset($type)) {
    $node = content_profile_load($type, $user->uid);
    if (!$node) {
      $node = array('uid' => $user->uid, 'name' => (isset($user->name) ? $user->name : ''), 'type' => $type, 'language' => '');
    }
    module_load_include('inc', 'node', 'node.pages');
    return drupal_get_form($type . '_node_form', $node);
  } else {
    return t('Application completed!');
  }
}