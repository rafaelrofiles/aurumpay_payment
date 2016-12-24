<?php

/**
 * Form definition for Smart Money Form.
 */
function aurumpay_payment_smartmoney_form($form, &$form_state, $user_id, $order_id) {
  $base = array(
    '#type' => 'textfield',
    '#required' => TRUE,
  );
  $hidden = array(
    '#type' => 'hidden',
    '#required' => TRUE,
  );
  $user = user_load($user_id);
  $order = commerce_order_load($order_id);
  if ( (bool)$order ) {
    $addressfield = array();
    
    $profile_id = field_get_items('commerce_order', $order, 'commerce_customer_billing');

    $customer_profile = commerce_customer_profile_load(isset($profile_id) ? $profile_id[0]['profile_id'] : 0);

    if ($customer_profile)
      $addressfield = field_get_items('commerce_customer_profile', $customer_profile, 'commerce_customer_address');

    $fee = ( !empty($order->commerce_order_total) ) ? $order->commerce_order_total['und'][0]['amount'] : FALSE;
    $fee = ( $fee ) ? $fee / 100 : 0;
    $fee = sprintf("%01.2f", $fee);

    $form['user_id'] = array(
      '#type' => 'hidden',
      '#value' => $user_id,  
    );
    $form['order_id'] = $hidden + array(
      '#value' => $order_id,
    );
    $form['payment_method'] = $hidden + array(
      '#value' => PAYMENT_METHOD_SMARTMONEY,
    );
    $form['country'] = $hidden + array(
      '#value' => 'PH',
    );
    $form['currency'] = $hidden + array(
      '#value' => 'PHP',
    );

    $form['order_id'] = array(
      '#title' => 'Order ID',
      '#type' => 'textfield',
      '#value' => $order_id,
      '#disabled' => TRUE,
    );
    $form['amount'] = $base + array(
      '#title' => 'Amount',
      '#value' => $fee,
      '#disabled' => TRUE,
    );
    $form['first_name'] = $base + array(
      '#title' => 'First Name',
      '#default_value' => $addressfield ? $addressfield[0]['first_name'] : '',
    );
    $form['last_name'] = $base + array(
      '#title' => 'Last Name',
      '#default_value' => $addressfield ? $addressfield[0]['last_name'] : '',
    );
    $form['address1'] = $base + array(
      '#title' => 'Address',
      '#default_value' => $addressfield ? $addressfield[0]['thoroughfare'] : '',
    );
    $form['city'] = $base + array(
      '#title' => 'City',
      '#default_value' => $addressfield ? $addressfield[0]['locality'] : '',
    );
    $form['zip_code'] = $base + array(
      '#title' => 'Zip Code',
      '#default_value' => $addressfield ? $addressfield[0]['postal_code'] : '',
    );
    $form['phone'] = $base + array(
      '#title' => 'Phone',
    );
    $form['email'] = $base + array(
      '#title' => 'Email',
      '#default_value' => $user ? $user->mail : '',
    );
    $form['addons'] = array(
      '#prefix' => '<div class="addons-wrapper">',
      '#suffix' => '</div>',
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Submit',
      '#validate' => array('aurumpay_payment_validate'),
      '#submit'   => array('aurumpay_payment_send_request'),
    );

    return $form;
  }
}