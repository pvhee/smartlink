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