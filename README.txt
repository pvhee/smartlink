Module Overwrites
=================

- content_profile.module:
  Remove the goto statement at line 383; if not it creates a wrong goto after a new user profile has been created.
  //drupal_goto('node/'. $nid .'/edit', 'destination=user/'. $node->uid);