<?php

class DrupalConnect {

  /**
   * @var
   * Holds the key of the app.
   */
  private $key;

  /**
   * @var
   * Holds the secret key of the app.
   */
  private $secret;

  /**
   * @var
   * The URL of the oAuth output.
   */
  private $url;

  /**
   * @var OAuthSignatureMethod
   * A unique oAuth signature of the app.
   */
  public $signature;

  /**
   * @var
   * The methods of the HTTP response.
   */
  private $method;

  /**
   * @var DrupalOAuthConsumer
   * The oAuth consumer object.
   */
  public $consumer;

  /**
   * @var OAuthToken
   * The oAuth token object.
   */
  public $token;

  /**
   * @var DrupalOAuthClient
   * The Drupal oAuth client object.
   */
  public $oauth;

  /**
   * @var DrupalOAuthRequest
   * The Drupal oAuth request object.
   */
  public $request;

  /**
   * Constructing the object.
   *
   * @param $key
   *  The key of the app.
   * @param $secret
   *  The secret key of the app.
   *
   * @return DrupalConnect
   *  The Drupal connect object after construction.
   */
  public function __construct($key, $secret) {
    $this->key = $key;
    $this->secret = $secret;
    $this->method = 'GET';

    $this->consumer = new DrupalOAuthConsumer($this->key, $this->secret);
    $this->token = new OAuthToken($this->key, $this->secret);
    $this->oauth = new DrupalOAuthClient($this->consumer, $this->token);
    $this->signature = $this->oauth->signatureMethod();
  }

  /**
   * Convert the oAuth request token to array.
   */
  private function RequestTokens() {
    return (array)$this->oauth->getRequestToken();
  }

  /**
   * Set the url for the oAuth request.
   * @param $url
   *  The URL.
   *
   * @return $this;
   */
  public function SetUrl($url) {
    $this->url = $url;
    return $this;
  }

  /**
   * Set the oAuth request object.
   * @return $this
   */
  public function SetOauthRequest() {
    $this->request = new DrupalOAuthRequest($this->method, $this->url, $this->RequestTokens());
    return $this;
  }

  /**
   * Set the signature parameter in the request object.
   *
   * @return $this
   */
  public function SetSignatureParameter() {
    $signature_text = $this->signature->build_signature($this->request, $this->consumer, $this->token);
    $this->request->set_parameter('signature', $signature_text);
    return $this;
  }

  /**
   * verify that the key and secret return the given signature.
   * @param $signature
   *  The signature supplied by the client.
   *
   * @return bool
   */
  public function VerifySignature($signature) {
    // TODO: Fix.
    return $this->signature->check_signature($this->request, $this->consumer, $this->token, $signature);
  }

  /**
   * Return the results from the oAuth provider.
   */
  public function getResult() {
    $headers = array(
      'Authorization' => 'Oauth',
      'Content-type' => 'application/x-www-form-urlencoded',
    );

    $url = $this->request->get_normalized_http_url() . '?';
    $url .= http_build_query($this->request->get_parameters(), '', '&');

    return drupal_http_request($url, array('headers' => $headers, 'method' => 'GET'));
  }
}
