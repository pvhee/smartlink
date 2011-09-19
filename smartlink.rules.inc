<?php

/**
* Implementation of hook_rules_event_info().
* @ingroup rules
*/
function smartlink_rules_event_info() {
  return array(
    'smartlink_user_update' => array(
      'label' => t('After updating a smartlink score for a user'),
      'module' => 'Smartlink',
      'arguments' => array(
        'node' => array('type' => 'node', 'label' => t('Smartlink node')),
        'user' => array('type' => 'user', 'label' => t('User')),
      ),
    ),
   'smartlink_user_applied' => array(
      'label' => t('After a user has applied for a smartlink'),
      'module' => 'Smartlink',
      'arguments' => array(
        'node' => array('type' => 'node', 'label' => t('Smartlink node')),
        'user' => array('type' => 'user', 'label' => t('User')),
      ),
    ),
   'smartlink_user_applied_firsttime' => array(
      'label' => t('After a user has applied for the first time to a smartlink'),
      'module' => 'Smartlink',
      'arguments' => array(
        'node' => array('type' => 'node', 'label' => t('Smartlink node')),
        'user' => array('type' => 'user', 'label' => t('User')),
      ),
    ),
   'smartlink_user_invited' => array(
      'label' => t('After a user has been invited for a smartlink'),
      'module' => 'Smartlink',
      'arguments' => array(
        'node' => array('type' => 'node', 'label' => t('Smartlink node')),
        'user' => array('type' => 'user', 'label' => t('User')),
      ),
    ),
  );
}

/**
 * Implementation of hook_rules_condition_info().
 *
 * @ingroup rules
 */
function smartlink_rules_condition_info() {
  return array(
    'smartlink_condition_score' => array(
      'label' => t('Smartlink score comparison'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Smartlink node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
      'module' => 'Smartlink',
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 *
 * Provides an action to invite the user to a smartlink node (to be configured).
 */
function smartlink_rules_action_info() {
  return array(
    'smartlink_action_invite_user_smartlink' => array(
      'label' => t('Invite user to given smartlink'),
      'arguments' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
      'module' => 'Smartlink',
      'eval input' => array('smartlink'),
    ),
  );
}


/**
 * Rules Condition form configuration - set the score to compare
 *
 * @see smartlink_rules_condition_info
 */
function smartlink_condition_score_form($settings = array(), &$form) {
  $form['settings']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#options' => array('greater' => t('Greater than'), 'equal' => t('Equal to'), 'less' => t('Less than')),
    '#default_value' => isset($settings['operation']) ? $settings['operation'] : 'equal',
  );

  $form['settings']['score'] = array(
    '#type' => 'textfield',
    '#title' => t('Score'),
    '#default_value' => isset($settings['score']) ? $settings['score'] : '',
    '#description' => t('The score to compare with.'),
  );
}

/**
 * Condition implementation: Numeric comparison.
 */
function smartlink_condition_score($node, $user, $settings) {
  $data = smartlink_get_data_user($user, $node, FALSE);
  $score = $data['percent'];
  $score_to_compare = $settings['score'];

  switch ($settings['operation']) {
    case 'greater':
      return $score > $score_to_compare;

    case 'equal':
      return $score == $score_to_compare;

    case 'less':
      return $score < $score_to_compare;
  }
}

function smartlink_action_invite_user_smartlink($user, $settings) {
  $uid = $user->uid;
  $nid = $settings['smartlink'];
  smartlink_set_invited_user_smartlink($uid, $nid);
}

function smartlink_action_invite_user_smartlink_form($settings, &$form) {
  $settings += array('smartlink' => '');

  $form['settings']['smartlink'] = array(
    '#type' => 'textarea',
    '#title' => t('Smartlink'),
    '#default_value' => $settings['smartlink'],
    '#description' => t('The smartlink the user is invited to.'),
  );
}