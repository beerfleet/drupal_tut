<?php

/**
 * @file
 * Admin page hooks for the annotate module.
 */

/**
 * Form builder. Config annotations.
 * 
 * @ingroup forms
 * @see system_settings_form().
 */
function annotate_admin_settings() {
  // Get an array of node types with internal names as keys and
  // friendly names as values E.g.,
  // array('page' => 'Basic page', 'article' => 'Articles')
  $types = node_type_get_types();
  foreach ($types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }

  $form['annotate_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('A text field will be available on these content types to make '
        . 'user-specific notes'),
    '#options' => $options,
    '#default_value' => variable_get('annotate_node_types', array('page')),
    '#description' => t('A text field will be available on these content types '
        . 'to make user-specific notes.'),
  );

  $form['annotate_deletion'] = [
    '#type' => 'radios',
    '#title' => t('Annotations will be deleted'),
    '#description' => t('Select a method for deleting annotations.'),
    '#options' => [
      t('Never'),
      t('Randomly'),
      t('After 30 days'),
    ],
    '#default_value' => variable_get('annotate_deletion', 0) // Default to never
  ];
  
  $form['annotate_limit_per_node'] = [
    '#type' => 'textfield',
    '#title' => t('Annotations per node'),
    '#description' => t('Enter the maximum number of annotations allowed per node (0 for no limit).'),
    '#default_value' => variable_get('annotate_limit_per_node', 1),
    '#size' => 3
  ];

  $form['#submit'][] = 'annotate_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Validate form submission
 */
function annotate_admin_settings_validate($form, &$form_state) {
  $limit = $form_state['values']['annotate_limit_per_node'];
  if (!is_numeric($limit)) {
    form_set_error('annotate_limit_per_node', t('Please enter number.'));
  }
}