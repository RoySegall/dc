<div class="dc_publisher_documentation">
  <p class="title"><?php print $title; ?></p>
  <p class="description"><?php print $description; ?></p>
  <p class="url><?php print $url; ?></p>

  <div id="<?php print $tab_id; ?>" class="dc_publisher_tabs">
    <ul class="list">
      <li><a href="#url" class="url"><?php print $t['url']; ?></a></li>
      <li><a href="#code" class="code"><?php print $t['code']; ?></a></li>
    </ul>
    <div id="url">
      <p><?php print $raw_url; ?></p>
    </div>

    <div id="code">
      <p><?php print $code; ?></p>
    </div>
  </div>
</div>
