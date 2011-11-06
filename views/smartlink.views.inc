<?php
// $Id$

/**
 *  @file
 *  Views integration.
 */

/**
 * Implementation of hook_views_data()
 */
function smartlink_views_data() {
  $data['smartlink']['table']['group']  = t('Smartlink');

  $data['smartlink']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('Smartlink'),
    'help' => t('Smartlinks'),
  );
  
  $data['smartlink']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
      'type' => 'INNER',
    ),
  );

  $data['smartlink']['nid'] = array(
    'title' => t('Smartlink nid'),
    'help' => t('The smartlink nid.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'smartlink_views_handler_argument_nid',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'smartlink_views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'label' => t('Node'),
      'handler' => 'views_handler_relationship',
    ),
  );

  $data['smartlink']['uid'] = array(
    'title' => t('Smartlink uid'),
    'help' => t('The smartlink uid.'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Users'),
      'handler' => 'views_handler_relationship',
    ),
  );


  $data['smartlink']['percent'] = array(
    'title' => t('Percent'),
    'help' => t('The smartlink percentage for this user.'),
    'field' => array(
      'handler' => 'smartlink_views_handler_field_percent',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['smartlink']['data'] = array(
    'title' => t('Smartlink Data'),
    'help' => t('The smartlink data of the user.'),
    'field' => array(
      'handler' => 'smartlink_views_handler_field_data',
      'click sortable' => FALSE,
    ),
  );

  $data['smartlink']['created'] = array(
    'title' => t('Application date'),
    'help' => t('The date the user applied for the smartlink.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['smartlink']['changed'] = array(
    'title' => t('Application updated date'),
    'help' => t('The date the user modified the application for the smartlink.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['smartlink']['invited'] = array(
    'title' => t('Invited'),
    'help' => t('Whether or not the user was invited for this smartlink.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Invited'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['smartlink']['applied'] = array(
    'title' => t('Applied'),
    'help' => t('Whether or not the user applied for this smartlink.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Applied'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function smartlink_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'smartlink') .'/views/handlers',
    ),
    'handlers' => array(
      // field handlers
      'smartlink_views_handler_field_percent' => array(
        'parent' => 'views_handler_field_custom',
      ),
      'smartlink_views_handler_field_data' => array(
        'parent' => 'views_handler_field_custom',
      ),
      'smartlink_views_handler_argument_nid' => array(
        'parent' => 'views_handler_argument_node_nid',
      ),
    ),
  );
}
