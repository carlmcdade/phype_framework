<?php foreach($posts as $key =>$item): ?>
    <div class="row">
		<div style="margin-bottom: 26px;" class="sixteen columns">
            <?php echo $cck->_view('page_content_blog_teaser',$item['container']['data']); ?>
            <span><?php echo $item['container']['ccid']; ?></span>
            <span><?php echo $cck->_format_datetime($item['container']['date_created']); ?></span>

            <?php $link['text'] = 'view'; ?>
            <?php $link['path'] = 'blog/post/view/'. $item['container']['ccid'] ; ?>
            <span><?php echo $cck->_link('links', $link); ?></span>
            <?php if($cck->_user_access() !== FALSE){ ?>
                <?php $link['text'] = 'edit'; ?>
                <?php $link['path'] = 'blog/post/edit/'. $item['container']['ccid'] ; ?>
                <span><?php echo $cck->_link('links', $link); ?></span>
            <?php } ?>

           <?php //echo $cck->_debug($item); ?>
        </div>
    </div>
<?php endforeach; ?>
<?php
/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 * @license FHQK Universal
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the FHQK Universal, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://cck.fhqk.com/license.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
?>