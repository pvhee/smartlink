<?php
// $Id$

/**
 *  @file
 *  Views integration.
 */

/**
 * Implementation of hook_views_data_alter().
 */
//function smartlink_views_data_alter(&$data) {
//  // smartlink relationship for user
//  $data['users']['smartlink_rel'] = array(
//    'group' => t('Node'),
//    'title' => t('Smartlink'),
//    'help' => t('Create a relationship to a smartlink of the user -- can be multiple!'),
//    'relationship' => array(
//      'handler' => 'views_handler_relationship',
//      'base' => 'node',
//      'base field' => 'uid',
//      'label' => t('Smartlink'),
//    ),
//  );
//}

/**
 * Implementation of hook_views_data()
 */
function smartlink_views_data() {
  $data['smartlink']['table']['group']  = t('Smartlink');
  
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

//  $data['smartlink']['completed'] = array(
//    'title' => t('Completed'),
//    'help' => t('Filter to view whether or not a node is 100% completed.'),
//    'filter' => array(
//      'real field' => 'completeness',
//      'title' => t('Completed'),
//      'handler' => 'smartlink_views_handler_filter_complete_nodes',
//      'type' => 'yes-no',
//    ),
//  );

  $data['smartlink']['data'] = array(
    'title' => t('Smartlink Data'),
    'help' => t('The smartlink data of the user.'),
    'field' => array(
      'handler' => 'smartlink_views_handler_field_data',
      'click sortable' => FALSE,
    ),
  );
  
//  $data['smartlink']['content_type'] = array(
//    'title' => t('Content type'),
//    'help' => t('Whether or not the content type is used for Content Complete.'),
//    'filter' => array(
//      'handler' => 'smartlink_views_handler_filter_content_type',
//      'label' => t('Is Content Complete enabled content type'),
//    ),
//  );
  
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
      
//      // filter handlers
//      'smartlink_views_handler_filter_content_type' => array(
//        'parent' => 'views_handler_filter_boolean_operator',
//      ),
//      'smartlink_views_handler_filter_complete_nodes' => array(
//        'parent' => 'views_handler_filter_boolean_operator',
//      ),
    ),
  );
}

/**
  * Implementation of hook_views_plugin().
  */
function smartlink_views_plugins() {
  return array(
    'module' => 'smartlink',
    'style' => array(
      'smartlink' => array(
        'path' => drupal_get_path('module', 'smartlink') . '/views/plugins',
        'title' => t('Content Complete'),
        'help' => t('Display completeness for a number of rows.'),
        'handler' => 'smartlink_style_plugin',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
