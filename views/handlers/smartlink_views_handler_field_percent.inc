<?php
// $Id$

/**
 *  @file
 *  This defines a view that outputs the completeness value of a node.
 */

class smartlink_views_handler_field_percent extends views_handler_field_custom {

  function option_definition() {
    $options = parent::option_definition();
    
    //$options['next'] = array('default' => FALSE, 'translatable' => TRUE);
    $options['display_as'] = array('default' => 'numeric', 'translatable' => TRUE);    
    
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $form['display_as'] = array(
      '#type' => 'select',
      '#title' => t('Display As'),
      '#options' => array(
    	  'numeric' => t('Numeric Value'),
    	  'bar' => t('Bar'),
    	),
      '#default_value' => $this->options['display_as'],
      '#description' => t('Choose how to display the percentage.'),
    );
    
//    $form['next'] = array(
//      '#type' => 'checkbox',
//      '#title' => t('Show next link.'),
//      '#default_value' => $this->options['next'],
//      '#description' => t('If checked, a message with a the next percent and a link to the page to complete this will be shown.'),
//    );
  }
	
  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field($this->table_alias, $this->real_field);
    $this->add_additional_fields();    
  }	
	
  function render($values) {    
    $data['percent'] = $values->{$this->field_alias};
        
    switch ($this->options['display_as']) {
      default:
      case 'numeric':
    	  return check_plain($data['percent']);
    	break;
    	case 'bar':
    	  // Render a separate message next to it.
        if ($this->options['next']) {
          $nid = $values->nid;
          $uid = $values->uid;
          $node = node_load($nid);
          $user = user_load($uid);
          $data = smartlink_get_data_user($node, $user);
        }
    	  return theme('smartlink_user', $data);
      break;    	
    }
  }
  
}
