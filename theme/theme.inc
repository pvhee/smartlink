<?php
// $Id$

/**
 * @file
 * Theme and template preprocessing code
 *
 * TODO refactor inside preprocess functions
 */

/**
 * Block Theme function that displays the default output of a content
 * complete percent. Use this theme function to override
 * the output / display of this block.
 *
 * @param $data
 *   Assoc array of
 *   ['type'] - str - The machine-readable name of this content type.
 *   ['name'] - str - The human-readable name of this content type.
 *   ['nid'] - int - The node ID of the node from this content type.
 *   ['percent'] - int - A number that represents the total percent complete (ie 50).
 *   ['leq_percent'] - int - A number that the current percent is lower or equal to (ie 25, 50, 75 or 100).
 *   ['completed'] - int - How many fields total that have been completed (filled out).
 *   ['incomplete'] - int - How many fields still need to be filled out.
 *   ['total'] - int - The count of all tagged profile fields.
 *   ['nextfield'] - str - The next field to fill out that is currently empty.
 *   ['nextpercent'] - int - What the total percent complete value will be when ['nextfield'] is complete.
 *   ['nextname'] - str - The field name of the next field for field focus.
 */
function theme_smartlink_user($data) {
  // add CSS for theming
  drupal_add_css(drupal_get_path('module', 'smartlink') .'/smartlink.css');

  $output .= '<div id="smartlink-wrapper" class="smartlink-complete-wrapper">';

//  if (isset($data['percent'])) {
//    $output .= t('!complete%', array(
//      '!complete' => $data['percent']
//    ));
//  }

  // Divide percentages in 4 regions of 25 each
  $data['leq_percent']=0;
  while ($data['leq_percent']<=100) {
    if ($data['percent'] <= $data['leq_percent']) break;
    $data['leq_percent']+=25;
  }

  if (!isset($data['percent'])) {
    $data['percent'] = 0; // protect against unset values
  }

  $output .= '<div id="smartlink-percent-bar-wrapper" class="smartlink-percent-bar-wrapper">';
  $output .= '<div id="smartlink-percent-bar" class="smartlink-percent-bar smartlink-percent-bar-leq-'. $data['leq_percent'] .' smartlink-percent-bar-'. $data['percent'] .'" style="width: '. $data['percent'] .'%"></div>';
  $output .= '</div>';
  $output .= '</div>';

  $output .= '<div id="smartlink-fields">';

  if (!isset($data['fields'])) {
    $data['fields'] = array();
  }
  
  foreach ($data['fields'] as $i => $field) {
    if (!$field['pass']) {
      switch ($field['operator']) {
        case 'leq':
          $operator_text = 'maximum';
          break;
        case 'geq':
          $operator_text = 'minimum';
          break;
        case 'eq':
          $operator_text = 'equal to';
          break;
        case 'neq':
          $operator_text = 'different from';
          break;
        default:
          continue;
      }
     $output .= '<div id="smartlink-field">';
     $output .= t('Fail! <i>!nextfield</i> needs to be !operator_text !smartlink_value.', array(
      '!nextfield' => l(t($field['label']), 'node/'. $data['nid'] .'/apply/'. $data['uid'] .'/'. $field['type_name']),
      '!operator_text' => $operator_text,
      '!smartlink_value' => $field['value'],
      ));
       $output .= '</div>';
    }
    else if (!$field['completed']) {
      $output .= '<div id="smartlink-field">';
      $output .= t('Fill out <i>!nextfield</i> for +!percent_complete%', array(
        '!nextfield' => l(t($field['label']), 'node/'. $data['nid'] .'/apply/'. $data['uid'] .'/'. $field['type_name']),
        '!percent_complete' => $field['percent_complete'],
      ));
      $output .= '</div>';
    } else {
      $output2 .= '<div id="smartlink-field">';
      $output2 .= t('Filled out <i>!nextfield</i>', array(
        '!nextfield' => l(t($field['label']), 'node/'. $data['nid'] .'/apply/'. $data['uid'] .'/'. $field['type_name']),
      ));
      $output2 .= '</div>';
    }
  }
  if (isset($output2)) $output .= $output2;
  $output .= '</div>';

//  if (isset($data['edit']) && $data['edit'] && isset($data['nextfield']) && isset($data['nextpercent'])) {
//    $output .= t('Filling out <i>!nextfield</i> will bring !typename to !complete%.', array(
//      '!nextfield' => l(t($data['nextfield']), 'node/'. $data['nid'] .'/edit', array(
//        'query' => 'content_complete_fieldname='. $data['nextname']
//      )),
//      '!typename' => $data['name'],
//      '!complete' => $data['nextpercent']
//    ));
//  }

  return $output;
}