<?php
global $cck;
//echo $cck->_debug($messages);

    if(isset($name) && !empty($messages))
    {

        echo '<div' . (isset($messages['class']) ? ' class="' . $messages['class']. '"' : '') .'>' ;
        echo '<ul>';

            foreach($messages['text'] as $text)
            {
                if(isset($text['message']))
                {
                    echo '<li>' . $text['message'] . '</li>' ."\n";
                }

            }

        echo '</ul>';
        echo '</div>';

    }
    elseif(!empty($messages))
    {



        foreach($messages as $name => $content)
        {
            echo '<div' . (isset($content['class']) ? ' class="' . $content['class']. '"' : '') .'>' ;
            echo '<ul>';
            foreach($content['text'] as $type => $message)
            {
                if(isset($message['message']))
                {
                    echo '<li>' . $message['message'] . '</li>' ."\n";
                }

            }
            echo '</ul>';
            echo '</div>';
        }


    }
?>
