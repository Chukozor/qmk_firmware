// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool is_accent_layer(void) {
  return layer_state_is(_ACCENTS);
  or:
  return IS_LAYER_ON(_ACCENTS); // which is just an alias
}

bool is_shift_layer(void) {
  return layer_state_is(_SFT_COLEMAK_FR);
  or:
  return IS_LAYER_ON(_SFT_COLEMAK_FR); // which is just an alias
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++