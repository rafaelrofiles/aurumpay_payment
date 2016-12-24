<?php

/**
 * Translates coded payment method to human-readable text.
 */
function _aurumpay_payment_humanize($string) {
  
  return $string;
}

/**
 * Returns AurumPay Logo markup.
 */
function _aurumpay_payment_aurumpay_logo() {
  return '<!--Aurumpay-->
          <p><a href="http://www.aurumpay.com/" target="_blank"><img src="http://www.aurumpay.com/img/aurumpay1.png" width="244" height="60"></a></p>
          <!--Aurumpay-->';
}

/**
 * Generates control for Send Request.
 */
function _aurumpay_payment_send_request_control($mid, $order_id, $amount, $email, $control_key) {

  return sha1($mid . $order_id . ($amount * 100) . $email . $control_key);
}

/**
 * Generates control for Status Request.
 */
function _aurumpay_payment_status_request_control($login, $client_orderid, $orderid, $merchant_control) {

  return sha1($login . $client_orderid . $orderid . $merchant_control);
}