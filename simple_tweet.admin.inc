<?php
/**
 * Admin Include Functions
 */
function simple_tweet_admin_settings($form_state) {
  $form = array();
  $form['simple_tweet_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Username'),
    '#required' => TRUE,
    '#default_value' => variable_get('simple_tweet_username', ''),
	'#description' => t('The username is needed to create a link to your Twitter account'),
  );
  $form['simple_tweet_rss_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter User RSS URL'),
    '#required' => TRUE,
    '#default_value' => variable_get('simple_tweet_rss_url', ''),
  );
  $form['simple_tweet_block_number'] = array(
  	'#type' => 'textfield',
	'#title' => t('Enter the number of tweets to show in multiple tweet block'),
	'#default_value'=> variable_get('simple_tweet_block_number', '1'),
  );  
  if(module_exists('date_api')) {
     $formats = date_get_format_types();
     $options = array();
     foreach($formats as $f) { 
       $key = $f['type'];
       if($key == 'short') $key = 'small';
       if($key == 'long') $key = 'large';
       $options[$key] = $f['title'];
     }
     $form['simple_tweet_dateformat'] = array(
       '#type' => 'select',
       '#options' => $options,
       '#title' => t('Date Format to Use'),
       '#default_value' => variable_get('simple_tweet_dateformat', 'medium'),
     );
     $form['#submit'][] = 'simple_tweet_admin_settings_submit';
  } else {
    $form['#prefix'] = '<p>'.t('For more control over date presentation insert the !date module.', array('!date' => l('Date API', 'http://www.drupal.org/project/date', array('absolute' => TRUE))));
  }

  $form['simple_tweet_tweets_page_title'] = array(
  	'#type' => 'textfield',
	'#title' => t('Enter Title for your Tweets Page'),
	'#default_value'=> variable_get('simple_tweet_page_title', 'Our Tweets From Twitter'),
	);
  $form['simple_tweet_tweets_path'] = array(
    '#type' => 'textfield',
    '#title' => 'Tweets Page Path',
    '#required' => TRUE,
    '#default_value' => variable_get('simple_tweet_tweets_path', 'our-tweets'),
    '#field_prefix' => 'http://'.$_SERVER['SERVER_NAME'].'/',
    '#description' => t('After you have changed this value, you MUST flush the cache in order for the changes to take effect. You can flush the cache !here', array('!here' => l('here', 'admin/settings/performance'))),
    );
  return system_settings_form($form);
}

/**
 * Admin form Validation
 */
function simple_tweet_admin_settings_submit($form, &$form_state) {
  if(!$form_state['values']['simple_tweet_rss_url']){ 
    form_set_error('simple_tweet_rss_url', t('Please Enter the Twitter Users RSS URL!'));
  }
  if(!$form_state['values']['simple_tweet_username']){ 
    form_set_error('simple_tweet_username', t('Please Enter your Twitter Username'));
  } 
}