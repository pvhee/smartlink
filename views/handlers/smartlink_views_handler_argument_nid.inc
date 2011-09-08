<?php
/**
 * Argument handler to accept a node id.
 */
class smartlink_views_handler_argument_nid extends views_handler_argument_node_nid {

  function option_definition() {
    $options = parent::option_definition();

    $options['smartlink_fields_limit'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['smartlink_fields_limit'] = array(
      '#type' => 'checkbox',
      '#title' => t('Limit Smartlink Fields.'),
      '#description' => t('If selected, only fields that are included in this smartlink will be rendered.'),
      '#default_value' => !empty($this->options['smartlink_fields_limit']),
    );
  }

  function query() {
    parent::query();

    /**
     * Extract smartlink node and information given the argument; this expects single values only for the argument!
     */
    if (!empty($this->options['smartlink_fields_limit'])) {
      $nid = $this->argument;
      $node = node_load($nid);
      $fields_smartlink = smartlink_get_tagged_fields($node);
      $fields_smartlink_db = array();
      foreach ($fields_smartlink as $field) {
        foreach ($field['columns'] as $column) {
          $fields_smartlink_db[] = $column;
        }
      }

      $fields = array();
      foreach (smartlink_get_field_content_types_options() as $type => $desc) {
        $fields += smartlink_get_fields($type);
      }
      $fields_db = array();
      foreach ($fields as $field_name => $field_data) {
        foreach ($field_data['columns'] as $column) {
          $fields_db[] = $column;
        }
      }

      $fields_unset = array_diff($fields_db, $fields_smartlink_db);
      foreach ($fields_unset as $field) {
        unset($this->view->field[$field]);
      }
    }

  }
}
