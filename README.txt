Description
===========
This module has one mission and one mission only: supply information from your
drupal site to external services with the oauth protocol.

How this is achieved?
===========
The model Drupal connect is basing on similar to what social networks(twitter,
facebook and even google) are using: there are apps that developers created.
Those apps have permissions on which data they can use. When external service,
like a mobile app or a site, asking to use the user information they have an api
key and a secret key which they passing through oAuth. If the uer approve the
app and the secret && API key are correct the data display in a JSON format on
which the mobile app uses the information.

Drupal connect create for people with the right permission to create an app. The
people on their site can use the oauth protocol to connect your drupal site with
the API and secret key and if the publisher module verified those credential he
will supply the information for the site.

Why should i use it?
==========
You should two main reasons for:
1.  You have a drupal site which allow to native apps connect with him and you
    want this in a security way.
2.  You have couple of drupal environments and you want to share data from a
    central one.

The modules and their usage:
==========
Drupal connect apps - Manage the apps the information they can use.
Drupal connect publisher -  Verify the oAuth credential and supply needed data.
Drupal connect reader - uses in Drupal site that ask information from other
                        Drupal sites.
